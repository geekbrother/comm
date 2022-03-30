use tonic::{transport::Server, Request, Response, Status};

use identity::identity_service_server::{IdentityService, IdentityServiceServer};

pub mod identity {
  tonic::include_proto!("identity");
}

#[derive(Debug, Default)]
pub struct MyIdentityService {}

#[tonic::async_trait]
impl IdentityService for MyIdentityService {
  async fn authenticate_user(&self, request: Request<()>) -> Result<Response<()>, Status> {
    println!("Got a request: {:?}", request);
    Ok(Response::new(()))
  }
  async fn verify_identity(&self, request: Request<()>) -> Result<Response<()>, Status> {
    println!("Got a request: {:?}", request);
    Ok(Response::new(()))
  }
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
  let addr = "[::]:50054".parse()?;
  let greeter = MyIdentityService::default();

  Server::builder()
    .add_service(IdentityServiceServer::new(greeter))
    .serve(addr)
    .await?;

  Ok(())
}
