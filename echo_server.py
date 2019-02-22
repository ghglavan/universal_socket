import socket

def listen():
    connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    connection.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    connection.bind(('localhost', 5555))
    connection.listen(1)
    while True:
        current_connection, address = connection.accept()
        data = current_connection.recv(4)
        if data:
            current_connection.send(data)
            print(data)
        else:
            print("no data received")


if __name__ == "__main__":
    try:
        listen()
    except KeyboardInterrupt:
        pass