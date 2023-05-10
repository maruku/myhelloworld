#include <fstream>	// for ofstream
#include <sys/mman.h> // for mmap
#include <fcntl.h>	// O_RDWR
#include <stdio.h>	// for printf
#include <string.h>	// for memcpy


typedef struct DRMScreenCapture_s {
	void *context;
	uint32_t width;
	uint32_t height;
	uint32_t pitch;
	uint8_t bpp;
}DRMScreenCapture;



void vector_write_file() {
//	std::ofstream textout("/tmp/screencapture.png", std::ios::out | std::ios::binary);
//        textout.write((const char*)&png_out_data[0], png_out_data.size());
}


void generate_spaerse_file_with_size(const char *name, unsigned int n) {
    std::ofstream ofs(name, std::ios::binary | std::ios::out);
    ofs.seekp(n);
    ofs.write("", 1);
    
}

void mmap_test(const char *name, unsigned int size) {
	printf("This is mmap_test\n");
	void *vaddr = NULL;
	uint8_t *buffer = NULL;
	buffer = (uint8_t *)malloc(size);
	memset(buffer, 1, size);
	// check if buffer contains right pattern
	for(int i=0; i<size; i++){
		if(buffer[i] != 1){
			printf("before buffer not ok, i=%d\n", i);
		}
	}
	
	
	printf("buffer=%p, size=%d, name=%s\n", buffer, size, name);
	
	int drm_fd = open(name, O_RDWR);
	
    vaddr =(void*) mmap(NULL, size, PROT_READ , MAP_SHARED, drm_fd, 0) ;
	printf("vaddr=%p\n", vaddr);
	
	memcpy(buffer,(unsigned char*)vaddr, size);
	munmap(vaddr, size); 
	
	// check if buffer contains right pattern
	for(int i=0; i<size; i++){
		if(buffer[i] != 0){
			printf("after buffer not ok, i=%d\n", i);
			break;
		}
	}
	
	free(buffer);
}


constexpr auto myfunc = &mmap_test;

int main() {
	const char* filename="ouput.img";
	unsigned int size = (1<<20) - 1;	// 1MB
    generate_spaerse_file_with_size(filename, size);
	myfunc(filename, size);


}

