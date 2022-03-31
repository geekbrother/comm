FROM rust:1.57

# Create a new user comm and use it to run subsequent commands
RUN useradd -m comm
USER comm

WORKDIR /app/identity
RUN cargo init --bin

COPY Cargo.toml Cargo.lock ./

# Cache build dependencies in a new layer
RUN cargo build --release
RUN rm src/*.rs

COPY . .

# Remove the previously-built binary so that only the application itself is
# rebuilt
RUN rm ./target/release/deps/identity*

# The build.rs script depends on rustfmt
RUN rustup component add rustfmt

RUN cargo build --release

CMD ["./target/release/identity"]
