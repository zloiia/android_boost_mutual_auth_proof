#!/bin/bash

openssl genrsa -aes256 -out ca.key 4096
openssl req -new -x509 -days 365 -key ca.key -out ca.crt -subj "/CN=192.168.88.2"

openssl genrsa -aes256 -out client.key 4096
openssl req -new -key client.key -out client.csr -subj "/C=AU"
openssl x509 -req -days 365 -in client.csr -CA ca.crt -CAkey ca.key -set_serial 01 -out client.crt



cp ca.key ca.key.secure
openssl rsa -in ca.key.secure -out ca.key

cp client.key client.key.secure
openssl rsa -in client.key.secure -out client.key

rm -rf client/certs

mkdir client/certs

cp client.crt client/certs/client.crt
cp client.key client/certs/client.key
cp ca.crt client/certs/ca.crt

rm -rf server/certs
mkdir server/certs
cp ca.key server/certs/ca.key
cp ca.crt server/certs/ca.crt

