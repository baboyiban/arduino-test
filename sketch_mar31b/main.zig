const c = @cImport({
    @cInclude("servo_wrapper.h");
});

pub fn main() !void {
    const servo = c.Servo_create();
    defer c.Servo_destroy(servo); // 자원 해제

    c.Servo_attach(servo, 6);
    c.Servo_write(servo, 90); // 90도로 이동
}
