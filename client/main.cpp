#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <QDebug>
#include <QFile>

enum {
    max_length = 1024
};

class client {
public:

    client(boost::asio::io_service& io_service, boost::asio::ssl::context& context,
            boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
    : socket_(io_service, context) {



        boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
        socket_.lowest_layer().async_connect(endpoint,
                boost::bind(&client::handle_connect, this,
                boost::asio::placeholders::error, ++endpoint_iterator));
    }

    std::string get_password() const {
        return "test";
    }

    void handle_connect(const boost::system::error_code& error,
            boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {
        if (!error) {
            socket_.async_handshake(boost::asio::ssl::stream_base::client,
                    boost::bind(&client::handle_handshake, this,
                    boost::asio::placeholders::error));
        } else if (endpoint_iterator != boost::asio::ip::tcp::resolver::iterator()) {
            socket_.lowest_layer().close();
            boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
            socket_.lowest_layer().async_connect(endpoint,
                    boost::bind(&client::handle_connect, this,
                    boost::asio::placeholders::error, ++endpoint_iterator));
        } else {
            qDebug() << "Connect failed: " << error;
        }
    }

    void handle_handshake(const boost::system::error_code& error) {
        if (!error) {
            //std::cout << "Enter message: ";
            //std::cin.getline(request_, max_length);
            strcpy(request_, "Hello");
            size_t request_length = 5;

            boost::asio::async_write(socket_,
                    boost::asio::buffer(request_, request_length),
                    boost::bind(&client::handle_write, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
        } else {
            qDebug() << "Handshake failed: " << error << "\n";
        }
    }

    void handle_write(const boost::system::error_code& error,
            size_t bytes_transferred) {
        if (!error) {
            boost::asio::async_read(socket_,
                    boost::asio::buffer(reply_, bytes_transferred),
                    boost::bind(&client::handle_read, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
        } else {
            qDebug() << "Write failed: " << error << "\n";
        }
    }

    void handle_read(const boost::system::error_code& error,
            size_t bytes_transferred) {
        if (!error) {
            qDebug() << "Reply: ";
            //std::cout.write(reply_, bytes_transferred);
            qDebug() << reply_;
            qDebug() << "\n";
        } else {
            qDebug() << "Read failed: " << error << "\n";
        }
    }

private:
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
    char request_[max_length];
    char reply_[max_length];
};


void exportFromResource(const QString &path, const QString &output_path)
{
    QFile f(path);
    QFile outfile(output_path);
    if (!f.open(QIODevice::ReadOnly) || !outfile.open(QIODevice::WriteOnly)) return;
    outfile.write(f.readAll());
    f.close();
    outfile.close();
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    boost::asio::io_service io_service;

    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query("192.168.88.2", "4444");
    boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);


    boost::asio::ssl::context ctx(io_service, boost::asio::ssl::context::sslv23);

    ctx.set_options(
           boost::asio::ssl::context::default_workarounds
             | boost::asio::ssl::context::no_sslv2
           | boost::asio::ssl::context::single_dh_use);
    ctx.set_verify_mode(boost::asio::ssl::context::verify_peer | boost::asio::ssl::context::verify_fail_if_no_peer_cert);

    exportFromResource(":/cert/certs/server.crt", "./server.crt");
    ctx.load_verify_file("./server.crt");

    ctx.use_certificate_chain_file("./server.crt");
    exportFromResource(":/cert/certs/server.key", "./server.key");
    ctx.use_private_key_file("./server.key", boost::asio::ssl::context::pem);
    exportFromResource(":/cert/certs/dh512.pem", "./dh512.pem");
    ctx.use_tmp_dh_file("./dh512.pem");

    client c(io_service, ctx, iterator);
    io_service.run();


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
