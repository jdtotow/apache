export LD_LIBRARY_PATH=/usr/local/lib64
g++ -std=c++11 -o main main.cpp -I/usr/include/mysql -L/usr/local/lib64 -lsoci_core -lsoci_mysql -ldl -lmysqlclient
-L/usr/local/lib64 -lsoci_core -lsoci_mysql -ldl -lmysqlclient