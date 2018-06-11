#if 0
notes can be anywhere within the #if 0 and the #endif

and they will be pretty printed

notes can contain any
number
of
lines
and any character !@#$%^&*()-=_+  /* */
#endif
int nl = __LINE__-4;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int mtime(char* path){
      struct stat att;
      stat(path, &att);
      return att.st_mtime;
}

int main(int argc, char* argv[]){
      if(*argv[0] == '.')argv[0] += 2;
      if(mtime(argv[0]) < mtime(__FILE__)){
            printf("recompile \"%s\" before running\n", __FILE__);
            return -1;
      }
      char fill = ' ';
      if(argc > 1)fill = *argv[1];
      FILE* fp = fopen(__FILE__, "r");
      fseek(fp, 6, SEEK_SET);
      size_t sz = 0;
      char* txt[nl]; unsigned char n=0, ml=0;
      int len;
      while(1){
            char* ln = NULL;
            sz = 0;
            if((len = getline(&ln, &sz, fp)) == EOF || !strncmp(ln, "#endif", 6)){
                  free(ln);
                  break;
            }
            ln[len-1] = '\0';
            txt[n++] = ln;
            if(len > ml)ml = len;
      }
      putchar(' ');
      for(int i = 0; i < ml; ++i){
            putchar('-');
      }
      putchar('\n');
      for(int i = 0; i < n; ++i){
            printf("|%s", txt[i]);
            for(int j = strlen(txt[i])+1; j < ml; ++j)putchar(fill);
            puts("|");
            free(txt[i]);
      }
      putchar(' ');
      for(int i = 0; i < ml; ++i){
            putchar('-');
      }
      putchar('\n');
      fclose(fp);
}
