#if 0
notes can be anywhere within the #if 0 and the #endif

and they will be pretty printed

... if a line begins with "..." it will not be pretty printed
anything following a "\..." on a line will not be pretty printed
                  ... these `comment` lines act the same as c style single line comments (//)
\... to print the string "\...", the escape character '\' can be used

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

int nlines(char* ef){
      FILE* fp;
      // TODO: add error handling for !fp
      if(ef)fp = fopen(ef, "r");
      else fp = fopen(__FILE__, "r");
      int ret = 0;
      char c;
      while((c = fgetc(fp)) != EOF)
            if(c == '\n')++ret;
      fclose(fp);
      return ret;
}

int main(int argc, char* argv[]){
      _Bool fill_all_ws = 0, fill_leading_ws = 0, info = 0;
      int force_width = 0;
      char* com_str = malloc(4); strncpy(com_str, "...", 3); com_str[3] = '\0';
      char* ex_file = NULL;
      for(int i = 1; i < argc; ++i){
            if(!strncmp(argv[i], "-i", 3))info = 1;
            if(!strncmp(argv[i], "-f", 3) && argc > i+1)ex_file = argv[i+1];
            if(!strncmp(argv[i], "-c", 3) && argc > i+1){
                  free(com_str);
                  com_str = argv[i+1];
            }
            if(!strncmp(argv[i], "-fa", 4))fill_leading_ws = fill_all_ws = 1;
            if(!strncmp(argv[i], "-fl", 4))fill_leading_ws = 1;
            if(!strncmp(argv[i], "-fw", 4))force_width = 1;
      }
      if(*argv[0] == '.')argv[0] += 2;
      if(!ex_file && mtime(argv[0]) < mtime(__FILE__)){
            printf("recompile \"%s\" before running\n", __FILE__);
            return -1;
      }
      char fill = ' ';
      if(argc > 1)fill = *argv[1];
      FILE* fp;
      if(ex_file)fp = fopen(ex_file, "r");
      else fp = fopen(__FILE__, "r");
      size_t sz = 0;
      if(ex_file || nl < 0)nl = nlines(ex_file);
      else fseek(fp, 6, SEEK_SET);
      char* txt[nl]; uint8_t n=0, ml=0;
      int nc = 0;
      uint32_t len;
      while(1){
            char* ln = NULL;
            sz = 0;
            if((len = getline(&ln, &sz, fp)) == EOF || !strncmp(ln, "#endif", 6)){
                  free(ln);
                  break;
            }
            char* com = ln;
            while((com = strstr(com, com_str))){
                  if(com > ln && *(com-1) == '\\'){
                        *(com-1) = *com_str;
                        uint32_t i = 0;
                        // -2 bc of \n
                        for(; i < len-(com-ln)-2; ++i)
                              com[i] = com[i+1];
                        com[i] = '\0';
                        --len;
                  }
                  else{
                        // TODO: should this skip line???
                        len -= strlen(com)-1;
                        *com = '\0';
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
      putchar('/');
      for(uint32_t i = 0; i < ml-1; ++i)
            putchar('-');
      puts("\\");
      // TODO: handle leading tabs
      for(uint32_t i = 0; i < n; ++i){
            printf("|%s", txt[i]);
            for(int j = strlen(txt[i])+1; j < ml; ++j)putchar(fill);
            puts("|");
            free(txt[i]);
      }
      putchar('\\');
      for(uint32_t i = 0; i < ml-1; ++i)
            putchar('-');
      puts("/");
      fclose(fp);
      if(info)printf("%i lines printed\n%i comment lines not printed\n", nl, nc);
}
