FROM rust:1.57

RUN USER=root cargo new --bin identity
WORKDIR /identity

COPY ./Cargo.lock ./Cargo.lock
COPY ./Cargo.toml ./Cargo.toml

RUN cargo build --release
RUN rm src/*.rs

COPY ./build.rs ./build.rs
COPY ./src ./src
COPY ./proto ./proto

RUN rm ./target/release/deps/identity*
RUN rustup component add rustfmt
RUN cargo install --path .

CMD ["identity"]