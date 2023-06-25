from flask import (
    Flask,
    jsonify,
    render_template,
    request
)
import os
import time
import subprocess
import json

carpeta_actual = os.getcwd()
carpeta_static = carpeta_actual + "/templates/static"

app = Flask(__name__, static_folder=carpeta_static)


@app.route('/')
def index():
    return render_template('index.html')


@app.route("/backpropagation", methods=['POST'])
def backpropagation():
    compilar = subprocess.run(["g++", carpeta_actual+"/test/inference/inference.cpp", "-o", "ejecutable"])
    if compilar.returncode == 0:
        matriz = request.get_json()['matriz']
        with open('matriz.json', 'w') as archivo:
                json.dump(matriz, archivo)
                resultado = subprocess.run(["./ejecutable"], input="matriz.json", text=True, capture_output=True)
    response = {"answer": "1"}
    return jsonify(response)


if __name__ == '__main__':
    app.run(debug=True, port=5000)
