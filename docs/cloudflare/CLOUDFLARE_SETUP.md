# Cloudflare Setup Guide

> **Status:** Stub — full content to be developed. See `README.md` for context.

## Overview

NeuroLift Technologies uses Cloudflare for infrastructure hosting and edge computing.

**Website:** neuroliftsolutions.com (Registered with Northwest Registered Agent)

## Services

| Service | Purpose |
|---|---|
| WordPress Hosting | Optimized performance and caching |
| Cloudflare Workers | Serverless edge computing |
| Cloudflare Pages | Static site hosting for documentation and app interfaces |
| CDN | Global content delivery for fast access |
| Security | DDoS protection, WAF, and bot mitigation |
| SSL/TLS | Automatic HTTPS and encryption |

## Quick Start

```bash
# Configure environment
cp cloudflare/.env.example cloudflare/.env

# Deploy everything
cd cloudflare/utils
./deploy.sh --all
```

## Directory Structure

```
cloudflare/
├── connector.py     ← Cloudflare API connector
├── workers/         ← Cloudflare Workers scripts
├── config/          ← Configuration files
└── utils/           ← Deployment and helper scripts
    └── deploy.sh
```

## Configuration

Edit `cloudflare/.env` with your Cloudflare credentials before deploying. Do not commit credentials to source control.

---

*For Cloudflare setup questions, escalate to Joshua W. Dorsey, Sr. (`info@neuroliftsolutions.com`).*
