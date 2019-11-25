
 violent i'm branch_01


-- 41

cd ~     : 进入根目录 
rm -r .ssh/      :删除之前生成的 
ssh-keygen -t rsa -C 1033580353@qq.com  
cd .ssh/   : 进入这个文件夹里 
ll    : 发现生成了 id_rsa  id_rsa.pub 
cat  id_rsa.pub   :复制里面的内容 
 github -> Settings -> SSH and  GPG keys  ,  新增一个SSH key ,把上面复制的粘贴进去



 
 gitlab下载：   https://packages.gitlab.com/gitlab/gitlab-ce/packages/el/7/gitlab-ce-10.8.2-ce.0.el7.x86_64.rpm
 
 
 
sudo rpm -ivh /opt/gitlab-ce-10.8.2-ce.0.el7.x86_64.rpm
sudo yum install -y curl policycoreutils-python openssh-server cronie
sudo lokkit -s http -s ssh
sudo yum install postfix
sudo service postfix start
sudo chkconfig postfix on
curl https://packages.gitlab.com/install/repositories/gitlab/gitlab-ce/script.rpm.sh | sudo bash
sudo EXTERNAL_URL="http://gitlab.example.com" yum -y 



9.4gitlab 服务操作
 初始化配置 gitlab
gitlab-ctl reconfigure
 启动 gitlab 服务
gitlab-ctl start
 停止 gitlab 服务
gitlab-ctl stop



policycoreutils-python is needed by gitlab-ce-10.8.2-ce.0.el7.x86_64   ： 这里需要安装policycoreutils：   https://zhidao.baidu.com/question/2075744946887140028.html 



/opt/gitlab/embedded/bin/ruby: /lib64/libc.so.6: version `GLIBC_2.14' not found (required by /opt/gitlab/embedded/lib/libruby.so.2.3)
/opt/gitlab/embedded/bin/ruby: /lib64/libc.so.6: version `GLIBC_2.17' not found (required by /opt/gitlab/embedded/lib/libruby.so.2.3)

https://blog.csdn.net/haoshidai/article/details/49210733?locationNum=13




https://blog.csdn.net/wangdw1984/article/details/82744651 





sudo rpm -ivh /opt/gitlab-ce-12.2.1-ce.0.el6.x86_64.rpm
sudo yum install -y curl policycoreutils-python openssh-server cronie
sudo lokkit -s http -s ssh
sudo yum install postfix
sudo service postfix start
sudo chkconfig postfix on
curl https://packages.gitlab.com/install/repositories/gitlab/gitlab-ce/script.rpm.sh | sudo bash
sudo EXTERNAL_URL="http://gitlab.example.com" yum -y install gitlab-ce



	公司服务器地址：  git@192.168.1.179:PuSong/lab_ps_01.git   annotation : ssh登录 IP后面跟的是：不是/   ， http登录才是/
 
 
  git@192.168.112.130/root/priv_slug_01.git    得换 ： git@192.168.1.178:root/priv_slug_01.git   用： http://192.168.1.178/root/priv_slug_01.git 
  git@192.168.112.130/root/publ_slug_01.git    得换 ： git@192.168.1.178:root/publ_slug_01.git   用： http://192.168.1.178/root/publ_slug_01.git 
 
 
 用：  git@192.168.1.178:root/publ_slug_01.git   可以 
 
 
  wh :   	https://blog.csdn.net/vtopqx/article/details/80883012  应该能设置权限
 
 
 
 经理发我： N_edition :      http://192.168.1.179/sunnychen/eps2016n.git  	用ssh:   	git@192.168.1.179:sunnychen/eps2016n.git
 
 
 
  
 
    http://192.168.1.179/sunnychen/lab_private_001.git    		git@192.168.1.179:sunnychen/lab_private_001.git
 
 
 
 
  jcrj2019666 
  XYT380088123555
  XYT380088123555m
  11111111
  111111
  
  
   
  
  

  
  
  
  
  
  
  
  
  
  
  
  






 
