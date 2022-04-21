use common::opaque::Cipher;
use opaque_ke::{ciphersuite::CipherSuite, rand::rngs::OsRng};
use std::{env, fs};

fn main() {
  let mut rng = OsRng;
  let server_kp = Cipher::generate_random_keypair(&mut rng);
  let mut path = env::current_dir().unwrap();
  path.push("secrets");
  if !path.exists() {
    println!("Creating secrets directory {:?}", path);
    fs::create_dir(&path).unwrap();
  }
  path.push("secret_key");
  println!("Writing secret key to {:?}", path);
  fs::write(&path, server_kp.private().to_arr()).unwrap();
}
