#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int app_name_num = 0;
// 文件
FILE *fp = NULL;
// 快捷方式名称
char app_name[30][20];
char app_name_b[200];
// 预留在 k-shell中使用?吧...
int log_status = 0;

// 判断是否为本程序指令
int is_parameter(char *);
// 判断名称是否在是否存在
int is_app_in_lnk(char *);
// 参数参数映射
int map_parameter(char *);
// 获取文件名称
int get_app(char *);

// 版本：0.1.0  更新时间：2020年3月3日    备注：雏形
// 版本：0.1.1  更新时间：2020年3月4日    备注：Keep模式
// 版本：0.1.2  更新时间：2020年3月7日    备注：添加了一些Linux命令
// 版本：0.1.3  更新时间：2020年12月13日  备注：更改文件格式为GBK解决乱码问题、添加Jupyter notebook

int main(int argc,char *argv[])
{
    char lnk[] = ".lnk";
    char file_dir[] = "D:\\Kuai\\";

    // 参数映射使用的变量
    int parameter;
    int i,j,len;
    // 参数
    char command[20];
    // keep 状态
    int keep_status = 0;
    // command = argv[1];
    // len = strlen(text_c);
    if(argv[1]){
        strcpy(command,argv[1]);
        // goto标记
        KEEP:
        // if '-'开头
        if (is_parameter(command)){
            parameter = map_parameter(command);
            // printf("%d",parameter);
            switch(parameter){
                // "k -h"
                case 1:
                    printf("欢迎使用 K(uai :)\n\n");
                    if (keep_status){
                        printf("  输入'-v' 查看版本\n");
                        printf("  Keep模式已经开启 'stop'可退出Keep模式\n");
                        printf("  输入'jn' 快速打开jupyter notebook\n");
                        printf("  目前支持的Linux相关指令：ls、su...\n");
                        printf("\n  支持快速打开添加快捷方式的软件('-d' 查看目录)\n");
                        
                    }
                    else{
                        printf("  输入'k -v' 查看版本\n");
                        printf("  输入'k keep' 进入Keep模式\n");
                        printf("  输入'k jn' 快速打开jupyter notebook\n");
                        printf("  目前支持的Linux相关指令：ls、su...\n");

                        printf("\n  支持快速打开添加快捷方式的软件('k -d' 查看目录)");
                    }
                    break;
                // "k -v"
                case 2:
                    if (keep_status){
                        printf("当前版本：0.1.3\n");
                        printf("最近更新时间：2020年12月13日\n");
                    }
                    else{
                        printf("当前版本：0.1.3\n");
                        printf("最近更新时间：2020年12月13日");
                    }
                    break;
                case 3:
                // "k -d"
                    printf("目录地址：%slnk\n",file_dir);
                    printf("已经添加的快捷方式有：\n");
                    if (!log_status)
                        get_app(file_dir);
                    len = strlen(app_name_b);
                    // 一行显示四个
                    // 从1开始排除 0%4=0 的情况
                    j = 1;
                    for(i = 0; i < len;i++){
                        if(app_name_b[i]=='\t' && j++%4==0){
                            printf("\n"); 
                        }
                        else
                            printf("%c",app_name_b[i]);
                    }
                    if(keep_status)
                        printf("\n");
                    break;
                default:
                    printf("未找到\n");
                    if(keep_status)
                        printf("输入'-h' 获取详情\n");
                    else
                        printf("输入'k -h' 获取详情");
            }
        }
        // 非指令(应用部分)
        else{
            // Keep 模式
            if(!strcmp(command,"keep")){
                if(!keep_status){
                    system("cls");
                    printf("Keep模式开启 'stop'可退出keep模式\n");
                    keep_status = 1;
                }
                else
                    printf("keep已经模式开启\n");
                // exit(0);
            }
            // 退出keep :)
            else if(!strcmp(command,"stop")){
                // system(argv[1]);
                // system("dir /b");
                exit(0); /* code */
            } // 查看文件
            else if(!strcmp(command,"ls")){
                // system(argv[1]);
                system("dir /b");
                // exit(0); /* code */
            }
            // 管理员权限 
            else if(!strcmp(command,"su")){
                strcat(command,lnk);
                system(command);
                // exit(0); 
            }
            // jupyter notebook 程序+指令
            else if(!strcmp(command,"jn")){
                system("jupyter notebook");
            }
            // 运行目录下的已添加的快捷方式
            else{
                if (!log_status)
                        get_app(file_dir);
                if(!is_app_in_lnk(command)){
                    strcat(command,lnk);
                    // printf(argv[1]);
                    system(command);
                    // system("cls");
                    // 关闭软件后退出
                    // exit(0); /* code */
                }
                else{
                    printf("对不起,输入的应用未添加\n");
                    if(keep_status){
                        printf("输入'-d' 获取已添加应用\n");
                        printf("输入'-h' 获取详情\n");
                    }
                    else{
                        printf("输入'k -d' 获取已添加应用\n");
                        printf("输入'k -h' 获取详情");
                    }
                    
                }
            }
        }
    }
    // 打印使用方法
    else{
        // printf("No inPut");
        // 输出目录
        // system("dir D:\\Kuai");
        printf("欢迎使用 K(uai)\n");
        printf("输入'k -h' 获取详情");
    }
    if (keep_status){
        printf(">> ");
        scanf("%s",command);
        goto KEEP;
    }
    return 0;
}
// 指令参数映射
int map_parameter(char *istc){
    if(!strcmp(istc,"-h"))
        return 1;
    else if(!strcmp(istc,"-v"))
        return 2;
    else if(!strcmp(istc,"-d"))
        return 3;
    else
        return 0;
}
// 判断是否为本程序指令
int is_parameter(char *istc){
    if(istc[0]=='-')
        return 1;
    else
        return 0;
}
int get_app(char *file_dir){
    int i,j,k,len;
    char dos_ins[100];
    char file_name[100];
    // 获取文件名称
    sprintf(dos_ins,"dir %slnk /b> %slog.txt",file_dir,file_dir);
    // system(" cd \"D:\\Kuai\" ; if ($?) { dir *.lnk} ; ");
    system(dos_ins);
    // 读取文件
    sprintf(file_name,"%slog.txt",file_dir);
    fp = fopen(file_name,"r");
    while (!feof(fp)){
        fgets(app_name[app_name_num],20,fp);
        // 替换换行符号
        len = strlen(app_name[app_name_num]);
        app_name[app_name_num][len - 1] = '\0';
        // printf("%s\n",app_name[app_name_num]);
        app_name_num++;
    }
    fclose(fp);
    k = 0;
    for(i = 0;i<app_name_num - 1;i++){
        for(j =0;j < 10;j++){
            // 排除部分程序名称和日志
            if(app_name[i][j]=='s' && app_name[i][j+1]=='u'&& app_name[i][j+2]=='.'){
                break;
            }
            // if(app_name[i][j]=='l' && app_name[i][j+1]=='o'&& app_name[i][j+2]=='g'){
            //     break;
            // }
            if(app_name[i][j]=='.'){
                app_name_b[k]= '\t';
                k++;
                break;
            }
            app_name_b[k] = app_name[i][j];
            k++;
        }
    }
    // 预留
    log_status = 1;
}
int is_app_in_lnk(char *input_name){
    int i,j,k;
    int input_len;
    int app_name_len;
    input_len = strlen(input_name);
    app_name_len = strlen(app_name_b);
    if(input_len>=app_name_len)
        return 1;
    else{
        for(i = 0;i<app_name_len;i++){
            // k作为一个长度标签
            k = 0;
            // 从检索每一元素的第一个开始
            if(i == 0|| app_name_b[i-1]=='\t'){
                for(j = 0;j<input_len;j++){
                    if(app_name_b[i] == input_name[j]){
                        i++;
                        k++;
                    }
                }
            // 长度与输入字符相等且后续没有其他字符
            if(k == input_len && app_name_b[i]=='\t')
                return 0;
            }
        }
        return 1;
    }
}