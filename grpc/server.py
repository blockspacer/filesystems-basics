import logging
import random
import string
import time
from concurrent import futures

import grpc
import helloworld_pb2
import helloworld_pb2_grpc


class Greeter(helloworld_pb2_grpc.GreeterServicer):
    def __init__(self):
        self.counter = random.randint(1, 100)
        self.char_set = string.ascii_letters + string.digits

    def SayHello(self, request, context):
        self.counter += 1
        if self.counter % 100 == 0:
            time.sleep(1)
        random_string = ''.join(random.choices(self.char_set, k=128))
        return helloworld_pb2.HelloReply(message=random_string)


def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    helloworld_pb2_grpc.add_GreeterServicer_to_server(Greeter(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    server.wait_for_termination()


if __name__ == '__main__':
    logging.basicConfig()
    serve()
