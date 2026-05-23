#![no_std]
#![no_main]

#[no_mangle]
pub extern "C" fn rust_add(a: i32, b: i32) -> i32{
    return a + b;
}

#[panic_handler]
fn panic(_info: &core::panic::PanicInfo) -> ! {
    loop {}
}