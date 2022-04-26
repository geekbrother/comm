use tonic::transport::Server;
use tracing_subscriber::FmtSubscriber;

mod service;
use service::{IdentityServiceServer, MyIdentityService};

const IDENTITY_SERVICE_SOCKET_ADDR: &str = "[::]:50051";

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
  let subscriber = FmtSubscriber::new();
  let _ =
    tracing::subscriber::set_global_default(subscriber).expect("Setting tracing default failed");
  let addr = IDENTITY_SERVICE_SOCKET_ADDR.parse()?;
  let mut identity_service = MyIdentityService::default();
  identity_service
    .config
    .load()
    .expect("Failed to load config successfully");

  Server::builder()
    .add_service(IdentityServiceServer::new(identity_service))
    .serve(addr)
    .await?;

  Ok(())
}
