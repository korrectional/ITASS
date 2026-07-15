# ESP32 Rust Quick Reference

## Cargo Commands

| Task | Command |
|---|---|
| Create project | `cargo generate esp-rs/esp-idf-template` |
| Build | `cargo build` |
| Release build | `cargo build --release` |
| Build + flash + monitor | `cargo run` |
| Flash only | `espflash flash target/xtensa-esp32-espidf/debug/<project_name>` |
| Serial monitor | `espflash monitor` |
| Check without building | `cargo check` |
| Clean | `cargo clean` |
| Format | `cargo fmt` |
| Lint | `cargo clippy` |
| Add dependency | `cargo add <crate>` |
| Update dependencies | `cargo update` |
| Generate docs | `cargo doc --open` |

## Project Structure

```text
src/
    main.rs
Cargo.toml
build.rs
sdkconfig.defaults
```

- `main.rs` — Application code
- `Cargo.toml` — Dependencies
- `build.rs` — Build configuration
- `sdkconfig.defaults` — ESP-IDF settings

## Rust Basics

### Variables

```rust
let x = 5;
let mut y = 10;
y += 1;
```

### Printing

```rust
println!("Hello!");
println!("Value: {}", x);
log::info!("Connected!");
log::warn!("Warning");
log::error!("Error");
```

### Functions

```rust
fn add(a: i32, b: i32) -> i32 {
    a + b
}
```

### Conditionals

```rust
if x > 5 {
} else {
}
```

### Match

```rust
match number {
    0 => println!("Zero"),
    1 => println!("One"),
    _ => println!("Other"),
}
```

### Loops

```rust
loop {}
while running {}
for i in 0..10 {}
```

### Structs

```rust
struct Led {
    pin: u8,
}
let led = Led { pin: 2 };
```

### Enums

```rust
enum State {
    Idle,
    Running,
}
```

### References

```rust
fn foo(x: &i32) {}
fn bar(x: &mut i32) {}
```

### Result

```rust
fn connect() -> Result<(), Error> {
    Ok(())
}
let result = connect()?;
match connect() {
    Ok(_) => {}
    Err(e) => {}
}
```

### Option

```rust
Some(5)
None
```

### Ownership

```rust
let a = String::from("hi");
let b = a; // ownership moves
let c = String::from("hi");
let d = &c; // borrow
```

### Imports

```rust
use esp_idf_hal::gpio::*;
```

### Traits

```rust
trait Animal {
    fn speak(&self);
}
```

## Useful Crates

- `esp-idf-hal`
- `esp-idf-svc`
- `embedded-hal`
- `log`
- `serde`
- `serde_json`
- `anyhow`

## Iroh Commands (P2P Networking)

### CLI

| Task | Command |
|---|---|
| Install iroh CLI | `cargo install iroh-cli` |
| Start node | `iroh start` |
| Node status | `iroh status` |
| Node ID | `iroh doctor id` |
| Send file | `iroh blob send <file>` |
| Fetch blob by ticket | `iroh blob get <ticket>` |
| List blobs | `iroh blob list` |
| Create doc | `iroh doc create` |
| Share doc | `iroh doc share <doc-id>` |
| Join doc | `iroh doc join <ticket>` |
| Set doc entry | `iroh doc set <doc-id> <key> <value>` |
| Get doc entry | `iroh doc get <doc-id> <key>` |
| Doctor/diagnostics | `iroh doctor report` |

### Rust API basics

```rust
use iroh::node::Node;

let node = Node::memory().spawn().await?;
let node_id = node.node_id();
```

```rust
// Blob transfer
let hash = node.blobs().add_bytes(data).await?;
let ticket = node.blobs().share(hash).await?;
```

```toml
# Cargo.toml
iroh = "0.x"
iroh-blobs = "0.x"
```

## ESP32 GPIO Commands (esp-idf-hal)

```rust
use esp_idf_hal::gpio::*;
use esp_idf_hal::peripherals::Peripherals;

let peripherals = Peripherals::take().unwrap();
let pins = peripherals.pins;
```

### Digital output

```rust
let mut led = PinDriver::output(pins.gpio2)?;
led.set_high()?;
led.set_low()?;
led.toggle()?;
```

### Digital input

```rust
let button = PinDriver::input(pins.gpio4)?;
if button.is_high() { }
button.set_pull(Pull::Up)?;
```

### PWM output

```rust
use esp_idf_hal::ledc::*;

let mut driver = LedcDriver::new(
    peripherals.ledc.channel0,
    LedcTimerDriver::new(peripherals.ledc.timer0, &config::TimerConfig::new())?,
    pins.gpio5,
)?;
driver.set_duty(driver.get_max_duty() / 2)?;
```

### ADC (analog read)

```rust
use esp_idf_hal::adc::*;

let mut adc = AdcDriver::new(peripherals.adc1, &AdcConfig::new())?;
let mut adc_pin = AdcChannelDriver::<{ attenuation::DB_11 }, _>::new(pins.gpio34)?;
let value: u16 = adc.read(&mut adc_pin)?;
```

### I2C

```rust
use esp_idf_hal::i2c::*;

let config = I2cConfig::new().baudrate(100.kHz().into());
let i2c = I2cDriver::new(peripherals.i2c0, pins.gpio21, pins.gpio22, &config)?;
```

### Delay

```rust
use esp_idf_hal::delay::FreeRtos;
FreeRtos::delay_ms(1000);
```

## Typical Workflow

```text
Edit code
    ↓
cargo check
    ↓
cargo build
    ↓
cargo run
    ↓
espflash monitor
```

## Remember

- Ownership prevents many memory bugs.
- `&` = borrow, `&mut` = mutable borrow.
- `Result` is for errors.
- `Option` is for values that may not exist.
- `?` propagates errors automatically.
- Traits are similar to interfaces.
