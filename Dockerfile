FROM gcc:10
WORKDIR /Operator-Precedence-Parsing/
COPY ./* ./
RUN g++ -Wall -Wextra -std=c++14 -O2 -fsanitize=address opg/.cpp -o program
RUN chmod +x program
