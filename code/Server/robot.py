import base64
from io import BytesIO
from PIL import Image


class Robot:
    def __init__(self):
        self.state = 0
        self.pose = {"x": 0.0, "y": 0.0, "theta": 0.0}
        self.nav_point = {"x": 0.0, "y": 0.0, "theta": 0.0}

    def get_state(self):
        return self.state

    def switch_state(self):
        self.state = 1 - self.state
        return self.state

    def get_map(self):
        map = Image.open("../map.pgm")
        output_buffer = BytesIO()
        map.save(output_buffer, format='JPEG')
        byte_data = output_buffer.getvalue()
        base64_str = base64.b64encode(byte_data)
        return base64_str.decode()

    def navigation(self, x, y, theta):
        self.nav_point['x'] = x
        self.nav_point['y'] = y
        self.nav_point['theta'] = theta
