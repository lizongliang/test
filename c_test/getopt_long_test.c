#include <stdio.h>
#include <getopt.h>

/*
 *getopt_long:参数先放在结构体option里面，函数返回结构体里面的val，最后一个参数
 *getopt:参数直接放在函数的optiongsting里面，一个冒号代表必须跟参数，俩个冒号代表可选
 */

/*
   int getopt_long(int argc, char * const argv[],
   const char *optstring,
   const struct option *longopts, int *longindex);

   struct option {
   const char *name;
   int has_arg;
   int *flag;
   int val;
   };
*/

/*
 *int getopt(int argc,char *argv[],const char *optstring )
 */

const struct option OPTION[] = {
    {"test_one",no_argument,NULL,'a'},
    {"test_two",no_argument,NULL,'b'},
    {"test_thr",no_argument,NULL,'c'},
};

int main(int argc,char *argv[])
{
    int result = 0;

#if 0
    result = getopt_long(argc,argv,"",OPTION,NULL);
#endif

    result = getopt(argc,argv,"ab:cd::e");

    if(result > 0 )
        printf("result is %c\n",result);

    return 0;
}
