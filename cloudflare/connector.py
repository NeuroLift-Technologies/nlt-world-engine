"""
connector.py — Cloudflare API connector for nlt-fusion

Status: Stub — full implementation pending Cloudflare integration phase.
See docs/cloudflare/CLOUDFLARE_SETUP.md for setup instructions.
"""


class CloudflareConnector:
    """Placeholder for Cloudflare API connector."""

    def __init__(self, api_token: str, account_id: str):
        self.api_token = api_token
        self.account_id = account_id

    def connect(self):
        raise NotImplementedError("CloudflareConnector not yet implemented.")
