from flask import (
    Flask,
    jsonify,
    render_template,
    request
)
import os
import time

carpeta_actual = os.getcwd()
carpeta_static = carpeta_actual + "/templates/static"

app = Flask(__name__, static_folder=carpeta_static)


@app.route('/')
def index():
    return render_template('index.html')


@app.route("/backpropagation", methods=['POST'])
def backpropagation():
    response = {"answer": 9}
    try:
        matriz = request.get_json()['matriz']
        time.sleep(10)
        print(matriz)
    except Exception as e:
        print(e)

    return jsonify(response)


if __name__ == '__main__':
    app.run(debug=True, port=5000)
