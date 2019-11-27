from datetime import datetime

import grpc
from termcolor import colored

import generator_pb2
import generator_pb2_grpc


def run(counter: int):
    start = datetime.now()
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = generator_pb2_grpc.GeneratorStub(channel)
        response = stub.generate(generator_pb2.GenRequest())
    timedelta = round((datetime.now() - start).total_seconds() * 1000, 1)
    color = 'red' if timedelta >= 1000 else 'green'
    print(colored(f'[{counter}] {response.text} Time: {timedelta} ms', color))


if __name__ == '__main__':
    for i in range(100):
        run(i)
