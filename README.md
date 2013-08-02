apt-get update
apt-get install git
apt-get install ia32-libs

git clone https://github.com/kirillian/ut3-server.git ut3-server
cd ut3-server

wget https://s3.amazonaws.com/dominate-gaming/UT3-linux-server-02202008-patch_1_2.bin -O binaries/UT3-linux-server-02202008-patch_1_2.bin
wget https://s3.amazonaws.com/dominate-gaming/UT3-linux-server-04292009-patch_1_3.bin -O binaries/UT3-linux-server-04292009-patch_1_3.bin
wget https://s3.amazonaws.com/dominate-gaming/UT3-linux-server-12172007.bin -O binaries/UT3-linux-server-12172007.bin

chmod +x binaries/UT3-linux-server-12172007.bin
chmod +x binaries/UT3-linux-server-02202008-patch_1_2.bin
chmod +x binaries/UT3-linux-server-04292009-patch_1_3.bin
./binaries/UT3-linux-server-12172007.bin
./binaries/UT3-linux-server-02202008-patch_1_2.bin
./binaries/UT3-linux-server-04292009-patch_1_3.bin

cp -r Config/ ~/ut3-dedicated/UTGame/
cp -r ut3-dedicated/ ~/

screen -dmLS ut3 ~/ut3-dedicated/Binaries/ut3 server CTF-Coret -login=admin

To look at the output:
screen -r ut3
