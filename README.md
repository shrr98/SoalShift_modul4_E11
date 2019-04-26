# SoalShift_modul4_E11

## Nomor 1

1. Membuat variabel global domain ( untuk menyimpan character list ) dan codomain ( untuk menyimpan hasil pemetaan setiap karakter dalam domain terhadap key ).
2. Membuat fungsi generateCodomain(int key) untuk meng-generate codomain dari domain dan key. codomain[0] = domain[key] dan seterusnya. Fungsi ini dipanggil akan dipanggil oleh fungsi main pertama kali.
3. Membuat fungsi dekrip(char \*nama). Fungsi ini mengubah setiap karakter dalam *nama* (kecuali karakter /) ke hasil dekripsinya, yaitu dengan cara mencari karakter di codomain. Setelah didapat index di codomain, idxDiCodomain, karakter diubah ke doman[idxDiCodomain].
4. Membuat fungsi enkrip(char \*nama). Fungsi ini mengubah setiap karakter dalam *nama* (kecuali karakter /) ke hasil enkripsinya, yaitu dengan cara mencari karakter di domain. Setelah didapat index di domain, idxDiDomain, karakter diubah ke codomain[idxDiDomain].
5. Membuat fungsi untuk mengimplementasikan .getattr, yaitu asf_getAttribute. Fungsi ini akan meng-enkripsi path relatif kemudian menggabungkan hasil enkripsi dengan dirpath menjadi fpath. Baru setelahnya fpath digunakan untuk pemanggilan fungsi lstat.
6. Membuat fungsi untuk mengimplementasikan .readdir, yaitu asf_readDir. Fungsi ini akan meng-enkripsi path relatifnya terlebih dahulu kemudia menggabungkan hasil enkripsi dengan dirpath menjadi fpath. Untuk setiap directory/file pada fpath, d_name didekripsi terlebih dahulu, baru setelahnya memanggil fungsi filler.
7. Membuat fungsi untuk  mengimplementasikan .read, yaitu asf_read. Fungsi ini akan meng-enkripsi terlebih dahulu path relatifnya, kemudian menggabungkan dengan dirpath menjadi fpath. Baru setelahnya membuka file fpath.
8. Membuat variable asf_oper bertipe struct fuse_operations yang berisi :
```c
.getattr	= asf_getAttribute,
.readdir	= asf_readDir,
.read		= asf_read,
  
```
9. Membuat fungsi main yang memanggil generateCodomain, set umask(0), kemudian me-return fuse_main
