# Contact Tracing Simulation Project

**Achievement**: This project was awarded a grade of 19 out of 20.

## Introduction
This project is a simulation of contact tracing functionalities similar to those used in COVID-19 contact tracing applications, such as "Stayaway Covid".
It aims to educate on the process of tracking and controlling the spread of diseases by utilizing data processing techniques in a simulated environment.

## Overview
The simulation represents a scenario where individuals move within a defined territory. Each individual is represented by a unique identifier and a set of coordinates.
Contacts are established when individuals come into close proximity. The simulation's goal is to track these contacts and identify potential risk contacts to control disease spread.

## Functionality
The program operates through command-line arguments, processing and outputting data to text files. It employs dynamic linked structures to store and manage contact data among simulated smartphones.

#### Supported Commands
- `-t`: Report total number of smartphones and contacts.
- `-n <Identifier1> <Identifier2> <x> <y> <day>`: Register a new contact.
- `-p <Identifier> <day>`: Search for contacts by identifier and day.
- `-m <Identifier1> <Identifier2>`: Find mutual contacts between two identifiers.
- `-a <Identifier> <day>`: Delete a contact for a given identifier on a specific day.
- `-i <Identifier> <day>`: Mark an identifier as infected on a given day.
- `-c <Identifier> <n_days>`: Determine chains of risk contacts originating from an identifier within `n_days`.

