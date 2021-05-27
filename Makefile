cc = g++
build_dir = ./build
prom = sugarscape
deps = main.h mapgen.h wormgen.h wormmove.h result.h
obj = main.o mapgen.o wormgen.o wormmove.o result.o

%.o : %.cpp $(deps)
	$(cc) -c $< -o $@ -I "D:\programe\Sugarscape" -g

$(prom):$(obj)
	$(cc) -o $(prom) $(obj)

clean:
	del $(obj) $(prom)