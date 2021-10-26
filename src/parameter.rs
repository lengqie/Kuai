// 对传入参数的一些处理

use super::files::read;
use super::files::run;

//参数判断
pub mod par {
    // 这个地方就有点烦...需要再次导入
    use super::super::files::read;

    //判断是否为自身参数
    pub fn is_para(pa: &str) -> bool {
        // no implementation for `str == &str`
        // let res = pa.starts_with("-");
        let res = &pa[0..1] == "-";
        if !res {
            return res;
        }
        // 长度判断
        if pa.len() == 2 {
            return true;
        }
        // println!("未知的参数： {}", &pa[1..]);
        false
    }
    // 判断是否为应用
    pub fn is_app(pa: &str) -> bool {
        let apps = read::app();
        for app in apps {
            if app == pa {
                // println!("App year~");
                return true;
            }
        }
        false
    }
    //判断是否为指令
    pub fn is_ins(pa: &str) -> bool {
        let ins_hash = read::ini();

        if !ins_hash.get(pa).is_none() {
            // println!("INS year~");
            return true;
        }
        return false;
    }
}

//参数
pub fn para(pa: &str) -> bool {
    match pa {
        "h" => {
            print!("欢迎使用 Kuai-rust :) rust\n\n");
            println!("  输入'k -v' 查看版本");
            println!("  支持快速打开添加快捷方式的软件('k -d' 查看目录)");
            println!("  目前支持的命令有");
            let ins_hash = read::ini();

            for (k, v) in ins_hash {
                println!("  k {}：{}",k,v);
            }
        }
        "v" => {
            print!("当前版本：0.2.0-rust\n最近更新时间：2021年9月2日")
        }
        "d" => {
            print!("已经添加的快捷方式有：");
            let apps = read::app();
            let mut i = 0;
            // 每行展示四个
            for app in apps {
                if i % 4 == 0 {
                    println!();
                }
                print!("{}\t", app);
                i += 1;
            }
        }
        _ => {
            // println!("未知的参数： {}", &pa);
            return false;
        }
    }
    return true;
}
//应用
pub fn app(app_name: &str) {
    let lnk = ".lnk";
    let command = app_name.to_string() + lnk;
    // println!("command year~{}",&command);
    run(&command);
}

//指令
pub fn ins(ins: &str) -> bool {
    let ins_hash = read::ini();

    for (k, v) in ins_hash {
        let k_s = format!("{}", k);
        let v_s = format!("{}", v);

        if k_s == ins {
            run(&v_s);
            return true;
        }
    }
    // println!("未知参数：{}",ins);
    return false;
}
