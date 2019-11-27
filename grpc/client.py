from __future__ import print_function

import logging
from datetime import datetime

import grpc
import helloworld_pb2
import helloworld_pb2_grpc
from termcolor import colored


def run(counter: int):
    start = datetime.now()
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = helloworld_pb2_grpc.GreeterStub(channel)
        response = stub.SayHello(helloworld_pb2.HelloRequest())
    timedelta = round((datetime.now() - start).total_seconds() * 1000, 1)
    color = 'red' if timedelta >= 1000 else 'green'
    print(colored(f'[{counter}] {response.message} Time: {timedelta} ms', color))


if __name__ == '__main__':
    logging.basicConfig()
    for i in range(1, 101):
        run(i)
