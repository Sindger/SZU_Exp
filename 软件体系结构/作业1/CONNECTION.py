class Connection:
    def connect(self):
        pass

    def disconnect(self):
        pass


class POP3Connection(Connection):
    def connect(self):
        print("Connect to POP3 server")

    def disconnect(self):
        print("Disconnect from POP3 server")


class IMAPConnection(Connection):
    def connect(self):
        print("Connect to IMAP server")

    def disconnect(self):
        print("Disconnect from IMAP server")


class HTTPConnection(Connection):
    def connect(self):
        print("Connect to HTTP server")

    def disconnect(self):
        print("Disconnect from HTTP server")


class ConnectionFactory:
    @staticmethod
    def create_connection(connection_type):
        if connection_type == "POP3":
            return POP3Connection()
        elif connection_type == "IMAP":
            return IMAPConnection()
        elif connection_type == "HTTP":
            return HTTPConnection()
        else:
            raise ValueError("Unsupported connection type")


if __name__=="__main__":
    try:
        protocol=input("Enter the protocol to connect: ")
        connection = ConnectionFactory.create_connection(protocol)
        connection.connect()
        connection.disconnect()
    except ValueError as e:
        print(str(e))