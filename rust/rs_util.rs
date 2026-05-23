#![no_std]
#![no_main]

#[no_mangle]
pub extern "C" fn RS_Int_To_Char(f: f64) -> const* u8{
    return "test alma";
}

#[panic_handler]
fn panic(_info: &core::panic::PanicInfo) -> ! {
    loop {}
}