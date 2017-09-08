# PAT-c10k-libev
## Deskripsi Tugas
Tugas Pengantar Aplikasi Terdistribusi (PAT) membuat applikasi server yang diharapkan dapat melayani 10000 concurrent connection dengan libev. Melakukan benchmark menggunakan apache benchmark tools dan membandingkan hasilnya dengan nginx/apache web server. 

## Pengujian 
Pengujian menggunakan ab (apache benchmark) untuk 2 file html static sebesar 20kb dan 500bytes
```
ab -c 10000 -n 100000 http://XX.XX.XX.XX/500b.html
ab -c 10000 -n 100000 http://XX.XX.XX.XX/20k.html
```

## Cara melakukan kompilasi
```
make
```

## Cara running program
```
./main
```

