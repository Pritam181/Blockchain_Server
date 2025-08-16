import hashlib
import json
from time import time
from uuid import uuid4
from flask import Flask, jsonify, request, render_template

class Blockchain:
    def __init__(self):
        self.chain = []
        self.current_transactions = []
        self.authorized_devices = {"ESP32-001", "ARDUINO-002"}  
        self.new_block(previous_hash='1', proof=100)  

    #creates a blockchain ledger with  blocks where each block has the address of prev block
    def new_block(self, proof, previous_hash=None):
        block = {
            'index': len(self.chain) + 1,
            'timestamp': time(),
            'transactions': self.current_transactions,
            'proof': proof,
            'previous_hash': previous_hash or self.hash(self.chain[-1]),
        }
        self.current_transactions = []
        self.chain.append(block)
        return block

    #create a new transaction block every time we mine
    def new_transaction(self, device_id, status):
        transaction = {
            'device_id': device_id,
            'status': status,
            'timestamp': time(),
            'hash': self.hash({"device_id": device_id, "status": status, "timestamp": time()})
        }
        self.current_transactions.append(transaction)
        return self.last_block['index'] + 1
    
    @staticmethod
    def hash(data):
        data_string = json.dumps(data, sort_keys=True).encode()
        return hashlib.sha256(data_string).hexdigest()
    
    @property
    def last_block(self):
        return self.chain[-1]

app = Flask(__name__)
blockchain = Blockchain()

@app.route('/')
def home():
    return render_template('index.html')
    
#to register device 
@app.route('/register_device', methods=['POST'])
def register_device():
    values = request.get_json()
    if not values:
        return jsonify({'message': 'No JSON data provided'}), 400
    device_id = values.get('device_id')
    if not device_id:
        return jsonify({'message': 'Missing device_id'}), 400
    blockchain.authorized_devices.add(device_id)
    return jsonify({'message': f'Device {device_id} registered successfully'}), 201
    
#to verify the device if its present in  the blockchain ledger or not
@app.route('/verify_device', methods=['POST'])
def verify_device():
    values = request.get_json()
    if not values:
        return jsonify({'message': 'No JSON data provided'}), 400
    device_id = values.get('device_id')
    if not device_id:
        return jsonify({'message': 'Missing device_id'}), 400

    if device_id in blockchain.authorized_devices:
        blockchain.new_transaction(device_id, "Authorized")
        return jsonify({'message': f'Device {device_id} is authorized'}), 200
    else:
        blockchain.new_transaction(device_id, "Unauthorized Attempt")
        return jsonify({'message': f'Device {device_id} is NOT authorized'}), 403

@app.route('/transactions', methods=['GET'])
def get_transactions():
    return jsonify({'transactions': blockchain.current_transactions})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080, debug=True)  



