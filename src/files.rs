use std::process::Command;

pub mod read{
    use std::fs;
    use std::fs::File;
    use std::io::prelude::*;
    use std::io::BufReader;
    use std::collections::HashMap;

    const KUAI_INI:&str = "kuai.ini";
    const KUAI_PATH:&str = "D:\\Kuai\\";


    pub fn app() ->Vec<String> {
        let mut res:Vec<String> = Vec::new();  
        let paths = fs::read_dir(KUAI_PATH.to_string() + "lnk").unwrap();
    
        for path in paths {

            //去掉目录信息的 后缀
            let a = &format!("{}", path.unwrap().path().display())[12..];

            let b = String::from(a);
            for name in b.split("."){
                res.push(name.to_string());
                break;
             }
        }
        return res;
    } 
    //返回的是新生成的String,有自己的生命周期,如果使用&str的话生命周期跟随他人
    pub fn ini()-> HashMap<String, String>{
        let path: &str = KUAI_INI;
        let mut hash:HashMap<String, String>  = HashMap::new();
    
        //let input: File = File::open(path)?;
        // 下面用法是不安全的...
        let input: File = File::open(KUAI_PATH.to_string() +path).unwrap();
        let buffered: BufReader<File> = BufReader::new(input);
    
        for line in buffered.lines().map(|x| x.unwrap()) {
            // line: String     x:Result<String, Error>
    
            // 暂时粗略处理
            if line.starts_with("#"){
                // println!("注释");
                continue;
            }
            if line.starts_with("["){
                // println!("节");
                continue;
            }
            let temp:Vec<&str>  = line.split("=").collect();
            hash.insert(temp[0].to_string(),temp[1].to_string());
        }
        return hash;
    }
}

pub fn run(cmd:&str){
    println!("run: {}",cmd);
    println!("---");
    // Command::new("cmd").arg("/c").arg(cmd).output().expect("cmd exec error!");
    let output = Command::new("cmd").arg("/c").arg(cmd).output().expect("cmd exec error!");
    let output_str = String::from_utf8_lossy(&output.stdout);
    let output_str = format!("{}",&output_str);
    print!("{}", output_str);
}