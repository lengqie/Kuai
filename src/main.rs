use std::env;

pub mod parameter;
pub mod files;

use parameter::par;
use parameter::para;
use parameter::app;
use parameter::ins;

/*
版本    时间            备注
0.2.0-rust   2021年9月2日    Rust重写 ini配置命令 移除keep模式 多参数待定 命令中文乱码未解决
*/
fn main() {
    let arg: Vec<_> = env::args().collect();
    let arg_len = arg.len();
    if arg_len == 1 {
        print!("欢迎使用 K(uai)\n输入'k -h' 获取详情");
    } else {
        let mut is_match = true;
        //参数
        if par::is_para(&arg[1]) {
            //不再传递 “-”
            is_match = para(&arg[1][1..]);
        }
        //应用
        else if par::is_app(&arg[1]) {
            app(&arg[1]);
        }
        //指令
        else{
            is_match = ins(&arg[1]);
        };
        if !is_match{
            println!("未知参数：{}",&arg[1]);
            print!("输入'k -h' 获取详情");
        }
    }
}