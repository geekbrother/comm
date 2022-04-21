use opaque_ke::keypair::Key;
use std::{env, fs, path::Path};

#[derive(Default, Debug)]
pub struct Config {
  server_secret_key: Option<Key>,
}

impl Config {
  pub fn load(&mut self) -> Result<(), Box<dyn std::error::Error>> {
    let mut path = env::current_dir()?;
    path.push("secrets");
    path.push("secret_key");
    let key = get_key_from_file(path)?;
    self.server_secret_key = Some(key);
    Ok(())
  }
}

fn get_key_from_file<P: AsRef<Path>>(path: P) -> Result<Key, Box<dyn std::error::Error>> {
  let bytes = fs::read(path)?;
  Key::from_bytes(&bytes).map_err(|e| e.to_string().into())
}
