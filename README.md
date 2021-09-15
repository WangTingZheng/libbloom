# libbloom

 [Origin project](https://github.com/jvirkki/libbloom) writen in C. The docment can be saw in https://zhuanlan.zhihu.com/p/407540513

 ## Using

 ```C++
 Bloom *bl = new Bloom(10000, 0.01);
 bl->add("helloworld", 10);
 if(bl->check("helloworld", 10)){
	cout << "helloworld is in the set" <<endl;
 }else{
	cout << "helloworld is not in the set" <<endl;
 }
 ```