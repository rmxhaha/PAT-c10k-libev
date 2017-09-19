# PAT-c10k-libev
## Deskripsi Tugas
Tugas Pengantar Aplikasi Terdistribusi (PAT) membuat applikasi server yang diharapkan dapat melayani 10000 concurrent connection dengan libev. Melakukan benchmark menggunakan apache benchmark tools dan membandingkan hasilnya dengan nginx/apache web server. 

## Pengujian 
Pengujian menggunakan ab (apache benchmark) untuk 2 file html static sebesar 20kb dan 500bytes
```
ab -c 500 -n 10000 http://XX.XX.XX.XX:PORT/500B.html
ab -c 500 -n 10000 http://XX.XX.XX.XX:PORT/20K.html
ab -c 1000 -n 10000 http://XX.XX.XX.XX:PORT/500B.html
ab -c 1000 -n 10000 http://XX.XX.XX.XX:PORT/20K.html
ab -c 10000 -n 10000 http://XX.XX.XX.XX:PORT/500B.html
ab -c 10000 -n 10000 http://XX.XX.XX.XX:PORT/20K.html
```
Setelah selesai akan diambil nilai p50 dan p99. Memory didapatkan dengan memperhatikan memory pada program htop.

File 500b dan 20kb di generasi mengunakan command
```
head -c 500 </dev/urandom >500B.html
head -c 20KB </dev/urandom >20KB.html
```


## Cara Instalasi depedency libev
```
sudo apt-get install -y libev-dev
sudo yum install -y libev-devel
```

## Cara melakukan kompilasi
```
make main
```


## Cara running program
```
./main <port> <root_path>
```
Secara default program akan running untuk root_path folder **html/** dan port **8192**.


## Hasil pengujian


Besar File (byte)|Jumlah Concurrent Request|Nginx|||Apache|||./main|||
---|---|---|---|---|---|---|---|---|---|---|
|||mem (MB)|p50 (ms)|p99 (ms)|mem (MB)|p50 (ms)|p99 (ms)|mem (MB)|p50 (ms)|p99 (ms)|
500|500|1.508|41|100|10.53|41|251|19|34|46|
500|1000|1.508|42|1041|23.12|42|1064|19|37|666|
500|10000|1.512|455|1483|154.8|48|2245|19|4098|11718|
20000|500|1.512|798|3360|64.34|500|2932|19|683|2474|
20000|1000|1.531|1226|14918|80.89|1060|13344|19|1501|6301|
20000|10000|1.512|1023|24990|185.6|3672|51155|19|9469|63268|Hanya Sampai 7516 connection


