

-- 41

cd ~ 
rm -r .ssh/      :删除之前生成的 
ssh-keygen -t rsa -C 1033580353@qq.com  
cd .ssh/   : 进入这个文件夹里 
ll    : 发现生成了 id_rsa  id_rsa.pub 
cat  id_rsa.pub   :复制里面的内容 
 github -> Settings -> SSH and  GPG keys  ,  新增一个SSH key ,把上面复制的粘贴进去



