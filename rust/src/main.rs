fn main() {
    let namep = add(13);

    let arr = [1, 2, 4];

    let len = arr.len();


    println!("after add {} {}", namep, len);
}

fn add(name: i32) -> i32 {
    name + 1
}