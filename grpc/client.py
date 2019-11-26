from __future__ import print_function

import logging
from datetime import datetime

import grpc
import helloworld_pb2
import helloworld_pb2_grpc


def run(counter: int):
    start = datetime.now()
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = helloworld_pb2_grpc.GreeterStub(channel)
        response = stub.SayHello(helloworld_pb2.HelloRequest(name='world'))
    timedelta = round((datetime.now() - start).total_seconds() * 1000, 2)
    print(f'[{counter}] {response.message} Time: {timedelta} ms')


if __name__ == '__main__':
    logging.basicConfig()
    for i in range(1, 101):
        run(i)
