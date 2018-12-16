make clean
rm -rf DOTS
make all-test
./pruebas_afnd
mkdir -p DOTS
mv *.dot DOTS
cd DOTS
for var in *.dot
do
dot -T gif $var > $var."gif"
#firefox $var."gif"&
done
