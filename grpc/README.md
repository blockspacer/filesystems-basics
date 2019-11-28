# gRPC server
This is simple server written in Python 
that generate random 128-byte string with random delay.

To run it you should make several steps:

Step 0:
 You should have Python 3.7+ on your machine.
 Install required packages.
```
$: pip install -r requirements.txt
```

Step 1: 
 Generate the gRPC client and server interfaces 
 from your `generator.proto` service definition
```
$: ./generate.sh
```

Step 2:
 Run the server
```
$: python server.py
```  

Now you have several options:


Option 1: use multiprocessing version of client.
It instantiates 16 servers balancing requests between the 
servers using the 
[`SO_REUSEPORT`](https://lwn.net/Articles/542629/) socket option.

```
$: python client.py
``` 

Option 2: use dummy single-process client. You can use via the 
additional proxy-server setting `use_proxy` option to `true` 
in `config.ini` or connect directly to server.

```
$: python proxy.py # if you want to use proxy
```
```
$: python dummy_client.py
```

Note: obviously, all programs should be run 
in different terminal windows.

Based on provided code [example](https://github.com/grpc/grpc/tree/master/examples/python/multiprocessing) by gRPC authors.
