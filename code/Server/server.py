from flask import Flask, request
import json
from database import DataBase

app = Flask(__name__)


@app.route("/", methods=["POST"])
def hello():
    data = json.loads(request.form.get("request"))
    response = {}
    if data['cmd'] == 'get_state':
        response['result'] = 1
        response['state'] = 1
    elif data['cmd'] == 'switch_state':
        response['result'] = 1
        response['state'] = 0
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
    app.run(host='0.0.0.0')
