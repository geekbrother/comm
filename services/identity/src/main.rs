use futures_core::Stream;
use std::pin::Pin;
use tonic::{transport::Server, Request, Response, Status};

use identity::identity_service_server::{IdentityService, IdentityServiceServer};
use identity::{AuthenticationRequest, AuthenticationResponse};

pub mod identity {
  tonic::include_proto!("identity");
}

#[derive(Debug, Default)]
pub struct MyIdentityService {}

#[tonic::async_trait]
impl IdentityService for MyIdentityService {
  type AuthenticateUserStream =
    Pin<Box<dyn Stream<Item = Result<AuthenticationResponse, Status>> + Send + 'static>>;

  async fn authenticate_user(
    &self,
    request: Request<tonic::Streaming<AuthenticationRequest>>,
  ) -> Result<Response<Self::AuthenticateUserStream>, Status> {
    println!("Got a request: {:?}", request);
    unimplemented!()
  }
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
  let addr = "[::]:50054".parse()?;
  let identity_service = MyIdentityService::default();

  Server::builder()
    .add_service(IdentityServiceServer::new(identity_service))
    .serve(addr)
    .await?;

  Ok(())
}
