# Random C Password Generator

A simple C program that generates random passwords with various options, designed to work on both Windows and Linux platforms.

## Features

- Generates random passwords based on user-defined criteria:
  - Password length
  - Inclusion of symbols
  - Inclusion of uppercase letters
- Secure random number generation using platform-specific methods:
  - Windows: CryptGenRandom function
  - Linux: /dev/urandom file
- Cross-platform compatibility

## Prerequisites

- For Windows users, no additional prerequisites are required.
- For Linux users, ensure you have `/dev/urandom available` for random number generation.

## Usage

1. Clone the repository to your local machine:

   `
   git clone https://github.com/your-username/random-password-generator.git
   `

2. Run the following command:

   `
   make
   `
3. Then you can run program with following command:

   `
   ./password_generator
   `
## Examples

```shell
./password_generator
Enter the length of the password: 50
Should the password contain symbols? (0/1): 1
Should the password contain uppercase letters? (0/1): 1
Generated Password: <BJ{vdR+IY+C(;Y-SvS?:W]AEM!rR@yPxjHkF|b|ka=Etie-xi
```

```shell
./password_generator
Enter the length of the password: 50
Should the password contain symbols? (0/1): 0
Should the password contain uppercase letters? (0/1): 0
Generated Password: gdhkprjvvkcqyshhabduetrrzvotelyhzcydjlxcfywykywnzv
```

```shell
./password_generator
Enter the length of the password: 50
Should the password contain symbols? (0/1): 0
Should the password contain uppercase letters? (0/1): 1
Generated Password: ipbzIStpeWLPfSnRmGmyYZmAkJfzEJTOvpsVJuPJLSHKANiChd
```

Copyright 2023, Max Base
