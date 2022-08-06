from werkzeug import Response
from flask import Blueprint, request
from flask.views import MethodView
import requests

widget_bp = Blueprint('widget', __name__)


class WeatherAPI(MethodView):

    def get(self) -> Response:

        args = request.args
        latitude: float = args.get('latitude')
        longitude: float = args.get('longitude')
        app_id: str = args.get('longitude')

        if latitude is None:
            raise Exception('Latitude argument was not provided')
        if longitude is None:
            raise Exception('Longitude argument was not provided')
        if app_id is None:
            raise Exception('App ID argument was not provided')

        url = 'https://api.openweathermap.org/data/2.5/weather?'

        url += f'lat={latitude}'
        url += f'lon={longitude}'
        url += f'appid={app_id}'

        return requests.get(url)

    def post(self) -> Response:
        pass

class NewsAPI(MethodView):

    def get(self) -> Response:
        pass

    def post(self) -> Response:
        pass


widget_bp.add_url_rule(
    '/weather', view_func=WeatherAPI.as_view('weather'), methods=['GET'])

widget_bp.add_url_rule(
    '/news', view_func=NewsAPI.as_view('news'), methods=[])

