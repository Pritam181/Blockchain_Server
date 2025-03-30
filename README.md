# Blockchain Server

## Overview
The Blockchain Server is a simple web application built using Flask that implements a basic blockchain for managing device authorization and transactions. It allows authorized devices to register and verify their status, while also maintaining a record of all transactions in the blockchain.

## Features
- Register new devices for authorization.
- Verify if a device is authorized or not.
- Maintain a blockchain to store transaction records.

## Installation
To set up the project, follow these steps:

1. Clone the repository:
   ```
   git clone https://github.com/yourusername/Blockchain_Server.git
   ```

2. Navigate to the project directory:
   ```
   cd Blockchain_Server
   ```

3. Install the required dependencies:
   ```
   pip install Flask
   ```

## Usage
1. Start the Flask server:
   ```
   python Blockchain_server.py
   ```

2. Access the application in your web browser at `http://localhost:8080`.

3. Use the following endpoints:
   - **Register Device**: Send a POST request to `/register_device` with a JSON body containing the `device_id` to register a new device.
   - **Verify Device**: Send a POST request to `/verify_device` with a JSON body containing the `device_id` to check if the device is authorized.
   - **Get Transactions**: Send a GET request to `/transactions` to retrieve the list of current transactions.

## Contributing
Contributions are welcome! Please feel free to submit a pull request or open an issue for any suggestions or improvements.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.