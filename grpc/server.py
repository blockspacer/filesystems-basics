import random
import string
import time
from concurrent import futures

import grpc

import generator_pb2
import generator_pb2_grpc


class Generator(generator_pb2_grpc.GeneratorServicer):
    def __init__(self):
        self.counter = random.randint(0, 99)
        self.char_set = string.ascii_letters + string.digits

    def generate(self, request, context):
        self.counter += 1
        if self.counter % 100 == 0:
            time.sleep(1)
        random_string = ''.join(random.choices(self.char_set, k=128))
        return generator_pb2.GenReply(text=random_string)


def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    generator_pb2_grpc.add_GeneratorServicer_to_server(Generator(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    server.wait_for_termination()


if __name__ == '__main__':
    serve()
