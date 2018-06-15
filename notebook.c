#if 0
notes can be anywhere within the #if 0 and the #endif

and they will be pretty printed

... if a line begins with "..." it will not be pretty printed
                  ... these `comment` lines can have any amount of leading whitespace
\... a leading "..." can be escaped with a \ to be pretty printed

notes can contain any
      number
            of
                  lines
and any character !@#$%^&*()-=_+  /* */
#endif
int nl = __LINE__-3;

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int mtime(char* path){
      struct stat att;
      stat(path, &att);
      return att.st_mtime;
}

int main(int argc, char* argv[]){
      _Bool fill_all_ws = 0, fill_leading_ws = 0;
      for(int i = 1; i < argc; ++i){
            if(!strncmp(argv[i], "-fa", 4))fill_leading_ws = fill_all_ws = 1;
            if(!strncmp(argv[i], "-fl", 4))fill_leading_ws = 1;
      }
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
      char* txt[nl]; uint8_t n=0, ml=0;
      uint32_t len;
      while(1){
            char* ln = NULL;
            sz = 0;
            if((len = getline(&ln, &sz, fp)) == EOF || !strncmp(ln, "#endif", 6)){
                  free(ln);
                  break;
            }
            char* com;
            if((com = strstr(ln, "..."))){
                  _Bool is_c = 1;
                  if(com > ln && *(com-1) == '\\'){
                        is_c = 0;
                        *(com-1) = '.';
                        uint32_t i = 0;
                        // -2 bc of \n
                        for(; i < len-(com-ln)-2; ++i)
                              com[i] = com[i+1];
                        com[i] = '\0';
                  }
                  else{
                        for(char* pos = ln; pos != com; ++pos)
                              if(*pos != ' '){
                                    is_c = 0;
                                    break;
                              }
                  }
                  if(is_c){
                        free(ln);
                        continue;
                  }
            }
            if((fill_all_ws || fill_leading_ws) && fill != ' ')
                  for(uint32_t i = 0; i < len; ++i){
                        if(ln[i] == ' ')ln[i] = fill;
                        else if(!fill_all_ws)break;
                  }
            ln[len-1] = '\0';
            txt[n++] = ln;
            if(len > ml)ml = len;
      }
      putchar(' ');
      for(uint32_t i = 0; i < ml; ++i)
            putchar('-');
      putchar('\n');
      for(uint32_t i = 0; i < n; ++i){
            printf("|%s", txt[i]);
            for(int j = strlen(txt[i])+1; j < ml; ++j)putchar(fill);
            puts("|");
            free(txt[i]);
      }
      putchar(' ');
      for(uint32_t i = 0; i < ml; ++i)
            putchar('-');
      putchar('\n');
      fclose(fp);
}
