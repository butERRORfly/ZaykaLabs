# usr/bin/bash

# создадим временный каталог Tmp и перейдем в него
mkdir Tmp
cd Tmp

# создадим 10 файлов в формате file_i.txt с помощью for и баз калк bc
touch $(echo 'for (i=1; i<=10; i++) {print "file_", i, ".txt\n"}' | bc)

# запишем содержимое директории (включая скрытые файлы) в file_1.txt
ls -la > file_1.txt

# вычислим пример 2+2 и дозапишем результат в file_1.txt
echo "2+2" | bc >> file_1.txt

# изменим file_1.txt на feli_1.txt и дозапишем в file_1.txt
echo file_1.txt | tr 'file_1' 'feli_1' >> file_1.txt

# запишем первые 4 строчки file_1.txt в новый файл answer.txt
head -n 4 file_1.txt > answer.txt

# дозапишем имя пользователя в answer.txt
echo who am I >> answer.txt

# создадим новую дирерторию answer и переместим в нее answer.txt
mkdir answer
mv answer.txt answer

# перейдем в новую директорию
cd answer

# скопируем file_1.txt в директорию answer
cp ../file_1.txt .

# зпищем содержимое файла file_1.txt в новый f22.txt
cat file_1.txt > f228.txt

# запишем в новый file.txt только те строчки из файла f228.txt,
# которые содержат слово "gleb"
grep "gleb" f228.txt | cat > file3.txt

# перейдем на уровень выше и рекурсивно удалим answer

# вспомним в какой мы директории
pwd

# создадим 10 файлов формата file_i.py
touch $(echo 'for (i=1; i<=10; i++) {print "file_",i,".py\n"}' | bc)

# переберем все файлы формата *.py и допишем в каждый из них
# необходимую конструкцию
for FILE in *
do
echo -e 'def main():\n\tpass\nif __name__ == "__main__":\n\tmain()' > "$FILE"
done
