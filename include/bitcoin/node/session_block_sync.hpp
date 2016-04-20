/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * libbitcoin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBBITCOIN_NODE_SESSION_BLOCK_SYNC_HPP
#define LIBBITCOIN_NODE_SESSION_BLOCK_SYNC_HPP

#include <cstddef>
#include <cstdint>
#include <memory>
#include <bitcoin/blockchain.hpp>
#include <bitcoin/network.hpp>
#include <bitcoin/node/define.hpp>
#include <bitcoin/node/hash_queue.hpp>
#include <bitcoin/node/reservations.hpp>
#include <bitcoin/node/settings.hpp>

namespace libbitcoin {
namespace node {

class BCN_API session_block_sync
  : public network::session_batch, track<session_block_sync>
{
public:
    typedef std::shared_ptr<session_block_sync> ptr;

    session_block_sync(network::p2p& network, hash_queue& hashes,
        blockchain::block_chain& chain, const settings& settings);

    void start(result_handler handler);

private:
    void handle_started(const code& ec, result_handler handler);
    void new_connection(network::connector::ptr connect,
        reservation::ptr row, result_handler handler);
    void handle_complete(const code& ec, network::connector::ptr connect,
        reservation::ptr row, result_handler handler);
    void handle_connect(const code& ec, network::channel::ptr channel,
        network::connector::ptr connect, reservation::ptr row,
        result_handler handler);
    void handle_channel_start(const code& ec, network::channel::ptr channel,
        network::connector::ptr connect, reservation::ptr row,
        result_handler handler);
    void handle_channel_stop(const code& ec, reservation::ptr row);

    // These are thread safe.
    blockchain::block_chain& blockchain_;
    reservations reservations_;

    const settings& settings_;
};

} // namespace node
} // namespace libbitcoin

#endif

