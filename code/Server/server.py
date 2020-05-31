from flask import Flask, request
import json
from database import DataBase
from robot import Robot

app = Flask(__name__)


@app.route("/", methods=["POST"])
def hello():
    data = json.loads(request.form.get("request"))
    response = {}
    if data['cmd'] == 'get_state':
        response['result'] = 1
        response['state'] = robot.get_state()
    elif data['cmd'] == 'switch_state':
        response['result'] = 1
        response['state'] = robot.switch_state()
    elif data['cmd'] == 'get_map':
        response['result'] = 1
        response['map'] = robot.get_map()
        response['pose_x'] = robot.pose['x']
        response['pose_y'] = robot.pose['y']
        response['pose_theta'] = robot.pose['theta']
    elif data['cmd'] == 'navigation':
        response['result'] = 1
        robot.navigation(data['x'], data['y'], data['theta'])
    elif data['cmd'] == 'log_in':
        response['result'] = 1
        response['log_in_result'] = db.logIn(data['user'], data['pwd'])
    elif data['cmd'] == 'sign_up':
        response['result'] = 1
        response['sign_up_result'] = db.signUp(data['user'], data['pwd'])
    elif data['cmd'] == 'advise':
        response['result'] = 1
        db.advice(data['advice'])
    else:
        response['result'] = -1
    return json.dumps(response)


if __name__ == "__main__":
    db = DataBase()
    robot = Robot()
    app.run(host='0.0.0.0')
