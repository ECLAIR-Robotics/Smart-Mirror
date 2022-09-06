from flask import Flask
import argparse
from widgets.handler import widget_bp

app = Flask(__name__)

app.register_blueprint(widget_bp, url_prefix='/widget')

if __name__ == '__main__':

    # Get the arguments of the given command
    parser = argparse.ArgumentParser(description=None)
    parser.add_argument('-d', '--debug', action='store_true',
                        help='Set the flask app to be in debug mode')
    parser.add_argument('--host', type=str, help='Set the host', default='0.0.0.0')
    parser.add_argument('--port', type=int, help='Set the port number', default=7000)
    args = parser.parse_args()

    app.run(debug=args.debug, host=args.host, port=args.port)